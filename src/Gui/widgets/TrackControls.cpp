/*****************************************************************************
 * TrackControls.cpp: Widget used to configure a track
 *****************************************************************************
 * Copyright (C) 2008-2010 VideoLAN
 *
 * Authors: Ludovic Fauvet <etix@l0cal.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#include <QIcon>
#include "GraphicsTrack.h"
#include "TrackControls.h"
#include "ui_TrackControls.h"

TrackControls::TrackControls( GraphicsTrack* track, QWidget *parent ) :
    QWidget( parent ), m_ui( new Ui::TrackControls ), m_track( track )
{
    m_ui->setupUi( this );
    setTrackDisabled( !m_track->isEnabled() );
    connect( m_ui->disableButton, SIGNAL( clicked(bool) ),
             this, SLOT( setTrackDisabled(bool) ) );
    updateTextLabels();
}

TrackControls::~TrackControls()
{
    delete m_ui;
}

void TrackControls::updateTextLabels()
{
    if ( m_track->mediaType() == MainWorkflow::VideoTrack )
        m_ui->trackLabel->setText( tr( "Video #%1" ).arg( QString::number( m_track->trackNumber() + 1 ) ) );
    else if ( m_track->mediaType() == MainWorkflow::AudioTrack )
        m_ui->trackLabel->setText( tr( "Audio #%1" ).arg( QString::number( m_track->trackNumber() + 1 ) ) );
}

void TrackControls::changeEvent( QEvent *e )
{
    QWidget::changeEvent( e );
    switch ( e->type() ) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi( this );
        updateTextLabels();
        break;
    default:
        break;
    }
}

void TrackControls::setTrackDisabled( bool disable )
{
    m_track->setTrackEnabled( !disable );
    if ( !disable )
    {
        if ( m_track->mediaType() == MainWorkflow::VideoTrack )
            m_ui->disableButton->setIcon( QIcon( ":/images/trackon" ) );
        else if ( m_track->mediaType() == MainWorkflow::AudioTrack )
            m_ui->disableButton->setIcon( QIcon( ":/images/hpon" ) );
    }
    else
    {
        if ( m_track->mediaType() == MainWorkflow::VideoTrack )
            m_ui->disableButton->setIcon( QIcon( ":/images/trackoff" ) );
        else if ( m_track->mediaType() == MainWorkflow::AudioTrack )
            m_ui->disableButton->setIcon( QIcon( ":/images/hpoff" ) );
    }
}
